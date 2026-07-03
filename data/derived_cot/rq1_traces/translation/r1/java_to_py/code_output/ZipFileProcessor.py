import zipfile
import logging
from pathlib import Path

class ZipFileProcessor:
    def __init__(self, zip_file_name):
        self.zip_file_path = Path(zip_file_name)
        self.logger = logging.getLogger(self.__class__.__name__)

    def _read_zip_file(self):
        if not self.zip_file_path.exists():
            self.logger.error(f"Zip file does not exist: {self.zip_file_path.absolute()}")
            return None
        try:
            return zipfile.ZipFile(self.zip_file_path, 'r')
        except Exception as e:
            self.logger.error(f"Failed to read the zip file: {self.zip_file_path.absolute()}", exc_info=True)
            return None

    def extract_all(self, output_dir):
        output_dir_path = Path(output_dir)
        try:
            zip_file = self._read_zip_file()
            if zip_file is None:
                return False
            with zip_file:
                if not output_dir_path.exists():
                    try:
                        output_dir_path.mkdir(parents=True, exist_ok=True)
                        self.logger.info(f"Created output directory: {output_dir_path.absolute()}")
                    except OSError as e:
                        self.logger.error(f"Failed to create output directory: {output_dir_path.absolute()}", exc_info=True)
                        return False

                for entry in zip_file.infolist():
                    full_path = output_dir_path / entry.filename
                    try:
                        if entry.is_dir():
                            if not full_path.exists():
                                full_path.mkdir(parents=True, exist_ok=True)
                                self.logger.info(f"Created directory: {full_path.absolute()}")
                        else:
                            with zip_file.open(entry) as in_file, open(full_path, 'wb') as out_file:
                                while True:
                                    chunk = in_file.read(1024)
                                    if not chunk:
                                        break
                                    out_file.write(chunk)
                                self.logger.info(f"Extracted file: {full_path.absolute()}")
                    except Exception as e:
                        self.logger.error(f"Failed to process entry: {entry.filename}", exc_info=True)
            return True
        except OSError as e:
            self.logger.error(f"Failed to extract files from zip: {self.zip_file_path.absolute()}", exc_info=True)
            return False

    def extract_file(self, file_name, output_dir):
        output_dir_path = Path(output_dir)
        file_path = output_dir_path / file_name
        try:
            zip_file = self._read_zip_file()
            if zip_file is None:
                return False
            with zip_file:
                try:
                    entry = zip_file.getinfo(file_name)
                except KeyError:
                    self.logger.warning(f"File not found in zip: {file_name}")
                    return False

                parent_dir = file_path.parent
                if not parent_dir.exists():
                    try:
                        parent_dir.mkdir(parents=True, exist_ok=True)
                        self.logger.info(f"Created parent directory: {parent_dir.absolute()}")
                    except OSError as e:
                        self.logger.error(f"Failed to create parent directory: {parent_dir.absolute()}", exc_info=True)
                        return False

                with zip_file.open(entry) as in_file, open(file_path, 'wb') as out_file:
                    while True:
                        chunk = in_file.read(1024)
                        if not chunk:
                            break
                        out_file.write(chunk)
                self.logger.info(f"Extracted file: {file_path.absolute()}")
            return True
        except OSError as e:
            self.logger.error(f"Failed to extract file: {file_name}", exc_info=True)
            return False