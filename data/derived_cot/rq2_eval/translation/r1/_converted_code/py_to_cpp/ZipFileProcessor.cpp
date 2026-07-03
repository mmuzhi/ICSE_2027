#include <unzip.h>
#include <zip.h>
#include <cstdio>
#include <string>
#include <memory>
#include <vector>
#include <cstring>
#include <cerrno>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

class ZipFile {
private:
    unzFile m_uf;

public:
    ZipFile(const std::string& file_name) : m_uf(unzOpen(file_name.c_str())) {
        if (!m_uf) {
            throw std::runtime_error("Failed to open zip file");
        }
    }

    ~ZipFile() {
        if (m_uf) {
            unzClose(m_uf);
        }
    }

    operator bool() const { return m_uf != nullptr; }
};

class ZipFileProcessor {
private:
    std::string file_name;

    static int mkdir_p(std::string path) {
        size_t pos = 0;
        int status = 0;

        while (pos < path.length()) {
            pos = path.find_first_of('/', pos + 1);
            std::string dir = path.substr(0, pos);

            if (dir.empty()) continue;

            status = mkdir(dir.c_str(), 0777);
            if (status != 0 && errno != EEXIST) {
                return status;
            }
        }
        return 0;
    }

    static bool extract_file_from_zip(unzFile uf, const std::string& output_path) {
        char filename_inzip[256];
        unz_file_info file_info;

        if (unzGetCurrentFileInfo(uf, &file_info, filename_inzip, sizeof(filename_inzip), nullptr, 0, nullptr, 0) != UNZ_OK) {
            return false;
        }

        std::string full_path = output_path + "/" + filename_inzip;
        size_t len = strlen(filename_inzip);

        if (len > 0 && filename_inzip[len - 1] == '/') {
            if (mkdir_p(full_path) != 0) {
                return false;
            }
        } else {
            std::string dir = full_path.substr(0, full_path.find_last_of('/'));
            if (!dir.empty() && mkdir_p(dir) != 0) {
                return false;
            }

            FILE* fout = fopen(full_path.c_str(), "wb");
            if (!fout) {
                return false;
            }

            if (unzOpenCurrentFile(uf) != UNZ_OK) {
                fclose(fout);
                return false;
            }

            char buffer[4096];
            int bytes_read;
            int err = UNZ_OK;

            while (true) {
                bytes_read = unzReadCurrentFile(uf, buffer, sizeof(buffer));
                if (bytes_read < 0) {
                    err = bytes_read;
                    break;
                }
                if (bytes_read == 0) {
                    break;
                }
                if (fwrite(buffer, 1, bytes_read, fout) != static_cast<size_t>(bytes_read)) {
                    err = -1;
                    break;
                }
            }

            if (err != UNZ_OK) {
                unzCloseCurrentFile(uf);
                fclose(fout);
                return false;
            }

            if (unzCloseCurrentFile(uf) != UNZ_OK) {
                fclose(fout);
                return false;
            }

            fclose(fout);
        }

        return true;
    }

    static bool read_zip_file(zipFile zf, const std::string& file) {
        size_t pos = file.find_last_of("/\\");
        std::string arcname = (pos == std::string::npos) ? file : file.substr(pos + 1);

        zip_fileinfo zi;
        memset(&zi, 0, sizeof(zi));

        FILE* fin = fopen(file.c_str(), "rb");
        if (!fin) {
            return false;
        }

        if (zipOpenNewFileInZip(zf, arcname.c_str(), &zi, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, Z_DEFAULT_COMPRESSION) != ZIP_OK) {
            fclose(fin);
            return false;
        }

        char buffer[4096];
        size_t bytes_read;

        while ((bytes_read = fread(buffer, 1, sizeof(buffer), fin)) > 0) {
            if (zipWriteInFileInZip(zf, buffer, bytes_read) != ZIP_OK) {
                zipCloseFileInZip(zf);
                fclose(fin);
                return false;
            }
        }

        if (ferror(fin)) {
            zipCloseFileInZip(zf);
            fclose(fin);
            return false;
        }

        zipCloseFileInZip(zf);
        fclose(fin);
        return true;
    }

public:
    ZipFileProcessor(const std::string& file_name) : file_name(file_name) {}

    std::shared_ptr<ZipFile> read_zip_file() {
        try {
            return std::make_shared<ZipFile>(file_name);
        } catch (...) {
            return nullptr;
        }
    }

    bool extract_all(const std::string& output_path) {
        try {
            unzFile uf = unzOpen(file_name.c_str());
            if (uf == nullptr) {
                return false;
            }

            unz_global_info global_info;
            if (unzGetGlobalInfo(uf, &global_info) != UNZ_OK) {
                unzClose(uf);
                return false;
            }

            bool success = true;
            for (uLong i = 0; i < global_info.number_entry; i++) {
                if (!extract_current_file(uf, output_path)) {
                    success = false;
                    break;
                }

                if (i < global_info.number_entry - 1) {
                    if (unzGoToNextFile(uf) != UNZ_OK) {
                        success = false;
                        break;
                    }
                }
            }

            unzClose(uf);
            return success;
        } catch (...) {
            return false;
        }
    }

    bool extract_file(const std::string& file_name_in_zip, const std::string& output_path) {
        try {
            unzFile uf = unzOpen(this->file_name.c_str());
            if (uf == nullptr) {
                return false;
            }

            if (unzLocateFile(uf, file_name_in_zip.c_str(), 0) != UNZ_OK) {
                unzClose(uf);
                return false;
            }

            bool success = extract_file_from_zip(uf, output_path);
            unzClose(uf);
            return success;
        } catch (...) {
            return false;
        }
    }

    bool create_zip_file(const std::vector<std::string>& files, const std::string& output_file_name) {
        try {
            zipFile zf = zipOpen(output_file_name.c_str(), 0);
            if (zf == nullptr) {
                return false;
            }

            bool success = true;
            for (const auto& file : files) {
                if (!add_file_to_zip(zf, file)) {
                    success = false;
                    break;
                }
            }

            zipClose(zf, nullptr);
            return success;
        } catch (...) {
            return false;
        }
    }
};