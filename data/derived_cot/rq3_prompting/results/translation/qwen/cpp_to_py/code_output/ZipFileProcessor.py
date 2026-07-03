import os
import zipfile
from typing import NamedTuple, List


class ZipFileInfo(NamedTuple):
    filename: str
    mode: str


class ZipFileProcessor:
    def __init__(self, zip_file_path: str):
        self.zip_file_path = zip_file_path

    def extract_all(self, output_directory: str) -> bool:
        if not output_directory:
            return False
        os.makedirs(output_directory, exist_ok=True)
        
        try:
            with zipfile.ZipFile(self.zip_file_path, 'r') as zipf:
                zipf.extractall(output_directory)
            return True
        except Exception as e:
            print(f"Error extracting files: {str(e)}", file=sys.stderr)
            return False

    def extract_file(self, file_name: str, output_directory: str) -> bool:
        if not output_directory:
            return False
        os.makedirs(output_directory, exist_ok=True)
        
        try:
            with zipfile.ZipFile(self.zip_file_path, 'r') as zipf:
                zipf.extract(member=file_name, path=output_directory)
            return True
        except FileNotFoundError:
            print(f"File not found in zip: {file_name}", file=sys.stderr)
            return False
        except Exception as e:
            print(f"Error extracting file: {str(e)}", file=sys.stderr)
            return False

    def create_zip_file(self, files: List[str], output_zip_file: str) -> bool:
        try:
            with zipfile.ZipFile(output_zip_file, 'w', zipfile.ZIP_DEFLATED) as zipf:
                for file_path in files:
                    if not os.path.exists(file_path):
                        print(f"File not found: {file_path}", file=sys.stderr)
                        continue
                    arcname = os.path.basename(file_path)
                    zipf.write(file_path, arcname=arcname)
            return True
        except Exception as e:
            print(f"Error creating zip file: {str(e)}", file=sys.stderr)
            return False

    def read_zip_file(self) -> ZipFileInfo:
        return ZipFileInfo(filename=self.zip_file_path, mode="r")