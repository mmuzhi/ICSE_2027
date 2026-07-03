import os
import logging
import zipfile
from pathlib import Path

class ZipFileProcessor:
    logger = logging.getLogger(__name__)
    logger.setLevel(logging.INFO)

    def __init__(self, zip_filename):
        self.zip_filename = Path(zip_filename)

    def read_zip_file(self):
        if not self.zip_filename.exists():
            self.logger.error(f"Zip file does not exist: {self.zip_filename.absolute()}")
            return None

        try:
            return zipfile.ZipFile(self.zip_filename, 'r')
        except zipfile.BadZipFile as e:
            self.logger.error(f"Failed to read the zip file: {self.zip_filename.absolute()}", e)
            return None
        except OSError as e:
            self.logger.error(f"Failed to read the zip file: {self.zip_filename.absolute()}", e)
            return None

    def extract_all(self, output_dir):
        output_dir_path = Path(output_dir)
        try:
            if not output_dir_path.exists():
                try:
                    os.makedirs(output_dir_path, exist_ok=True)
                    self.logger.info(f"Created output directory: {output_dir_path.absolute()}")
                except OSError as e:
                    self.logger.error(f"Failed to create output directory: {output_dir_path.absolute()}", e)
                    return False

            zip_file = self.read_zip_file()
            if zip_file is None:
                return False

            try:
                for entry in zip_file.namelist():
                    entry_path = output_dir_path / entry
                    if entry_path.is_dir():
                        if not entry_path.exists():
                            os.makedirs(entry_path, exist_ok=True)
                            self.logger.info(f"Created directory: {entry_path.absolute()}")
                    else:
                        parent_dir = entry_path.parent
                        if not parent_dir.exists():
                            try:
                                os.makedirs(parent_dir, exist_ok=True)
                                self.logger.info(f"Created parent directory: {parent_dir.absolute()}")
                            except OSError as e:
                                self.logger.error(f"Failed to create parent directory: {parent_dir.absolute()}", e)
                                continue

                        with zip_file.open(entry) as source:
                            with open(entry_path, 'wb') as target:
                                while True:
                                    chunk = source.read(1024)
                                    if not chunk:
                                        break
                                    target.write(chunk)
                        self.logger.info(f"Extracted file: {entry_path.absolute()}")

                return True
            except Exception as e:
                self.logger.error(f"Failed to extract files from zip: {self.zip_filename.absolute()}", e)
                return False
            finally:
                if zip_file:
                    zip_file.close()
        except Exception as e:
            self.logger.error(f"Failed to prepare output directory: {output_dir_path.absolute()}", e)
            return False

    def extract_file(self, file_name, output_dir):
        output_dir_path = Path(output_dir)
        file_path = output_dir_path / file_name

        zip_file = self.read_zip_file()
        if zip_file is None:
            return False

        try:
            try:
                entry = zip_file.getinfo(file_name)
            except KeyError:
                self.logger.warning(f"File not found in zip: {file_name}")
                return False

            if not file_path.parent.exists():
                try:
                    os.makedirs(file_path.parent, exist_ok=True)
                    self.logger.info(f"Created parent directory: {file_path.parent.absolute()}")
                except OSError as e:
                    self.logger.error(f"Failed to create parent directory: {file_path.parent.absolute()}", e)
                    return False

            with zip_file.open(file_name) as source:
                with open(file_path, 'wb') as target:
                    while True:
                        chunk = source.read(1024)
                        if not chunk:
                            break
                        target.write(chunk)
            self.logger.info(f"Extracted file: {file_path.absolute()}")
            return True
        except Exception as e:
            self.logger.error(f"Failed to extract file: {file_name}", e)
            return False
        finally:
            if zip_file:
                zip_file.close()