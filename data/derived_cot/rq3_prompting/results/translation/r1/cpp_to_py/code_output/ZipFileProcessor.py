import zipfile
import os
import sys


class ZipFileInfo:
    def __init__(self, filename: str = "", mode: str = "") -> None:
        self.filename = filename
        self.mode = mode


class ZipFileProcessor:
    def __init__(self, zip_file_path: str) -> None:
        self._zip_file_path = zip_file_path

    def read_zip_file(self) -> ZipFileInfo:
        info = ZipFileInfo()
        archive = self._open_zip_file("r")
        if archive is not None:
            info.filename = self._zip_file_path
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
        try:
            for name in archive.namelist():
                output_file_path = output_directory + "/" + name
                if not self._extract_file_from_zip(archive, name, output_file_path):
                    success = False
        finally:
            archive.close()
        return success

    def extract_file(self, file_name: str, output_directory: str) -> bool:
        if not output_directory:
            return False

        if not self._create_directory_if_not_exists(output_directory):
            print(f"Failed to create output directory: {output_directory}", file=sys.stderr)
            return False

        archive = self._open_zip_file("r")
        if archive is None:
            return False

        success = True
        try:
            # Check if file exists in zip
            try:
                archive.getinfo(file_name)
            except KeyError:
                print(f"File not found in zip: {file_name}", file=sys.stderr)
                return False

            output_file_path = output_directory + "/" + file_name
            success = self._extract_file_from_zip(archive, file_name, output_file_path)
        finally:
            archive.close()
        return success

    def create_zip_file(self, files: list[str], output_zip_file: str) -> bool:
        try:
            archive = zipfile.ZipFile(output_zip_file, "w", zipfile.ZIP_DEFLATED)
        except Exception as e:
            print(f"Error opening zip file: {output_zip_file}", file=sys.stderr)
            return False

        for file_path in files:
            try:
                archive.write(file_path, arcname=file_path)
            except Exception as e:
                print(f"Error adding file to zip: {file_path} ({e})", file=sys.stderr)
                archive.close()
                # Remove incomplete zip file? Not done in original.
                return False

        try:
            archive.close()
        except Exception as e:
            print(f"Error closing zip file: {output_zip_file} ({e})", file=sys.stderr)
            return False

        return True

    # ----- private helpers -----

    def _extract_file_from_zip(self, archive: zipfile.ZipFile, entry_name: str, output_file_path: str) -> bool:
        try:
            zfile = archive.open(entry_name, "r")
        except Exception:
            print(f"Failed to open file in zip: {entry_name}", file=sys.stderr)
            return False

        try:
            # Ensure parent directory exists? Original does not, so let it fail if missing.
            with open(output_file_path, "wb") as out_file:
                while True:
                    buf = zfile.read(4096)
                    if not buf:
                        break
                    out_file.write(buf)
        except Exception as e:
            print(f"Failed to write to file: {output_file_path} ({e})", file=sys.stderr)
            return False
        finally:
            zfile.close()
        return True

    def _create_directory_if_not_exists(self, dir_path: str) -> bool:
        try:
            os.makedirs(dir_path, exist_ok=True)
            return True
        except Exception:
            return False

    def _open_zip_file(self, mode: str):
        try:
            return zipfile.ZipFile(self._zip_file_path, mode)
        except Exception as e:
            print(f"Failed to open zip file: {self._zip_file_path} ({e})", file=sys.stderr)
            return None