import logging
import zipfile
from pathlib import Path
import shutil

logger = logging.getLogger(__name__)


class ZipFileProcessor:

    def __init__(self, zip_file_name: str):
        self.zip_file_path = Path(zip_file_name)

    def _read_zip_file(self):
        if not self.zip_file_path.exists():
            logger.error("Zip file does not exist: " + str(self.zip_file_path.resolve()))
            return None
        try:
            return zipfile.ZipFile(str(self.zip_file_path), 'r')
        except OSError:
            logger.error("Failed to read the zip file: " + str(self.zip_file_path.resolve()), exc_info=True)
            return None

    def extract_all(self, output_dir: str) -> bool:
        output_dir_path = Path(output_dir)
        zip_file = self._read_zip_file()
        if zip_file is None:
            return False
        try:
            if not output_dir_path.exists():
                try:
                    output_dir_path.mkdir(parents=True, exist_ok=True)
                    logger.info("Created output directory: " + str(output_dir_path.resolve()))
                except OSError:
                    logger.error("Failed to create output directory: " + str(output_dir_path.resolve()), exc_info=True)
                    return False

            for entry in zip_file.infolist():
                file_path = output_dir_path / entry.filename
                try:
                    if entry.is_dir():
                        if not file_path.exists():
                            file_path.mkdir(parents=True, exist_ok=True)
                            logger.info("Created directory: " + str(file_path.resolve()))
                    else:
                        with zip_file.open(entry) as in_stream, open(file_path, 'wb') as out_stream:
                            shutil.copyfileobj(in_stream, out_stream, 1024)
                        logger.info("Extracted file: " + str(file_path.resolve()))
                except OSError:
                    logger.error("Failed to process entry: " + entry.filename, exc_info=True)

            return True
        except OSError:
            logger.error("Failed to extract files from zip: " + str(self.zip_file_path.resolve()), exc_info=True)
            return False
        finally:
            zip_file.close()

    def extract_file(self, file_name: str, output_dir: str) -> bool:
        output_dir_path = Path(output_dir)
        file_path = output_dir_path / file_name
        zip_file = self._read_zip_file()
        if zip_file is None:
            return False
        try:
            try:
                entry = zip_file.getinfo(file_name)
            except KeyError:
                entry = None
            if entry is None:
                logger.warning("File not found in zip: " + file_name)
                return False

            parent = file_path.parent
            if not parent.exists():
                try:
                    parent.mkdir(parents=True, exist_ok=True)
                    logger.info("Created parent directory: " + str(parent.resolve()))
                except OSError:
                    logger.error("Failed to create parent directory: " + str(parent.resolve()), exc_info=True)
                    return False

            with zip_file.open(entry) as in_stream, open(file_path, 'wb') as out_stream:
                shutil.copyfileobj(in_stream, out_stream, 1024)
            logger.info("Extracted file: " + str(file_path.resolve()))

            return True
        except OSError:
            logger.error("Failed to extract file: " + file_name, exc_info=True)
            return False
        finally:
            zip_file.close()