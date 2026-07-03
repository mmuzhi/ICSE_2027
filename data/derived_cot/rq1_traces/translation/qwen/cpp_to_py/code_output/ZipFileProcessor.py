import os
import zipfile
from pathlib import Path

class ZipFileInfo:
    def __init__(self, filename, mode):
        self.filename = filename
        self.mode = mode

class ZipFileProcessor:
    def __init__(self, zip_file_path):
        self.zip_file_path_ = zip_file_path

    def read_zip_file(self):
        return ZipFileInfo(self.zip_file_path_, "r")

    def extract_all(self, output_directory):
        if not output_directory:
            return False
        
        if not self.create_directory_if_not_exists(output_directory):
            return False
        
        try:
            with zipfile.ZipFile(self.zip_file_path_, 'r') as zipf:
                zipf.extractall(output_directory)
            return True
        except zipfile.BadZipFile:
            print("Error: The file is not a valid ZIP file.")
            return False
        except Exception as e:
            print(f"An error occurred: {e}")
            return False

    def extract_file(self, file_name, output_directory):
        if not output_directory:
            return False
        
        if not self.create_directory_if_not_exists(output_directory):
            return False
        
        try:
            with zipfile.ZipFile(self.zip_file_path_, 'r') as zipf:
                try:
                    zipf.extract(file_name, output_directory)
                    return True
                except KeyError:
                    print(f"File not found in zip: {file_name}")
                    return False
                except Exception as e:
                    print(f"An error occurred while extracting {file_name}: {e}")
                    return False
        except zipfile.BadZipFile:
            print("Error: The file is not a valid ZIP file.")
            return False
        except Exception as e:
            print(f"An error occurred: {e}")
            return False

    def create_zip_file(self, files, output_zip_file):
        if not files:
            print("Error: No files provided to create the zip.")
            return False
        
        try:
            with zipfile.ZipFile(output_zip_file, 'w') as zipf:
                for file_path in files:
                    full_path = Path(file_path).resolve()
                    if not os.path.exists(full_path):
                        print(f"Error: File not found: {file_path}")
                        return False
                    zipf.write(file_path, os.path.basename(file_path), zipfile.ZIP_STORED)
            return True
        except Exception as e:
            print(f"Error creating zip file: {e}")
            return False

    def create_directory_if_not_exists(self, dir_path):
        Path(dir_path).mkdir(parents=True, exist_ok=True)
        return os.path.isdir(dir_path)

# Example usage:
# processor = ZipFileProcessor("example.zip")
# processor.extract_all("output_dir")
# processor.extract_file("file.txt", "output_dir")
# processor.create_zip_file(["file1.txt", "file2.txt"], "new_zip.zip")