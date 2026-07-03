import os
import sys
import zipfile
from dataclasses import dataclass


@dataclass
class ZipFileInfo:
    filename: str
    mode: str


class ZipFileProcessor:
    def __init__(self, zip_file_path: str):
        self.zip_file_path_ = zip_file_path

    def read_zip_file(self) -> ZipFileInfo:
        archive = self._open_zip_file("r")
        info = ZipFileInfo(filename="", mode="")
        if archive is not None:
            info.filename = self.zip_file_path_
            info.mode = "r"
            archive.close()
        return info

    def extract_all(self, output_directory: str) -> bool:
        if not output_directory:
            return False

        if not self._create_directory_if_not_exists(output_directory):
            return False

        archive = self._open_zip_file("r")
        if archive is None:
            return False

        success = True
        namelist = archive.namelist()
        for i, name in enumerate(namelist):
            output_file_path = output_directory + "/" + name
            if not self._extract_file_from_zip(archive, i, output_file_path):
                success = False

        archive.close()
        return success

    def extract_file(self, file_name: str, output_directory: str) -> bool:
        if not output_directory:
            return False

        if not self._create_directory_if_not_exists(output_directory):
            print(
                f"Failed to create output directory: {output_directory}",
                file=sys.stderr,
            )
            return False

        archive = self._open_zip_file("r")
        if archive is None:
            return False

        namelist = archive.namelist()
        try:
            index = namelist.index(file_name)
        except ValueError:
            print(f"File not found in zip: {file_name}", file=sys.stderr)
            archive.close()
            return False

        output_file_path = output_directory + "/" + file_name
        success = self._extract_file_from_zip(archive, index, output_file_path)

        archive.close()
        return success

    def create_zip_file(self, files: list, output_zip_file: str) -> bool:
        try:
            archive = zipfile.ZipFile(output_zip_file, "w")
        except Exception:
            print(f"Error opening zip file: {output_zip_file}", file=sys.stderr)
            return False

        for file_path in files:
            try:
                archive.write(file_path, file_path)
            except Exception:
                print(f"Error adding file to zip: {file_path}", file=sys.stderr)
                archive.close()
                return False

        try:
            archive.close()
        except Exception:
            print(f"Error closing zip file: {output_zip_file}", file=sys.stderr)
            return False

        return True

    def _extract_file_from_zip(
        self, archive: zipfile.ZipFile, index: int, output_file_path: str
    ) -> bool:
        name = archive.namelist()[index]
        try:
            data = archive.read(name)
        except Exception:
            print(f"Failed to open file in zip: {name}", file=sys.stderr)
            return False

        try:
            out_file = open(output_file_path, "wb")
        except OSError:
            print(f"Failed to open output file: {output_file_path}", file=sys.stderr)
            return False

        try:
            out_file.write(data)
        except Exception:
            print(f"Failed to write to file: {output_file_path}", file=sys.stderr)
            out_file.close()
            return False

        out_file.close()
        return True

    def _create_directory_if_not_exists(self, dir_path: str) -> bool:
        if not os.path.exists(dir_path):
            try:
                os.makedirs(dir_path)
                return True
            except OSError:
                return False
        return True

    def _open_zip_file(self, flags: str):
        try:
            archive = zipfile.ZipFile(self.zip_file_path_, flags)
            return archive
        except Exception:
            print(f"Failed to open zip file: {self.zip_file_path_}", file=sys.stderr)
            return None