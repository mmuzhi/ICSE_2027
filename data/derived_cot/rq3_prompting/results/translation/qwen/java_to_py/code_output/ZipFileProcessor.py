import logging
from pathlib import Path
import zipfile
import os

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

class ZipFileProcessor:
    def __init__(self, zip_filename):
        self.zip_file_path = Path(zip_filename)
    
    def read_zip_file(self):
        if not self.zip_file_path.exists():
            logger.error(f"Zip file does not exist: {self.zip_file_path.absolute()}")
            return None
        
        try:
            return zipfile.ZipFile(self.zip_file_path, 'r')
        except zipfile.BadZipFile as e:
            logger.error(f"Failed to read the zip file: {self.zip_file_path.absolute()}", e)
            return None

    def extract_all(self, output_dir):
        output_dir_path = Path(output_dir)
        try:
            zip_file = self.read_zip_file()
            if zip_file is None:
                return False

            if not output_dir_path.exists():
                try:
                    output_dir_path.mkdir(parents=True, exist_ok=True)
                    logger.info(f"Created output directory: {output_dir_path.absolute()}")
                except OSError as e:
                    logger.error(f"Failed to create output directory: {output_dir_path.absolute()}", e)
                    return False

            for info in zip_file.filelist:
                file_path = output_dir_path / info.filename
                if info.is_dir():
                    try:
                        file_path.mkdir(parents=True, exist_ok=True)
                        logger.info(f"Created directory: {file_path.absolute()}")
                    except OSError as e:
                        logger.error(f"Failed to create directory: {file_path}", e)
                        return False
                else:
                    try:
                        with zip_file.open(info) as in_file:
                            with open(file_path, 'wb') as out_file:
                                while True:
                                    chunk = in_file.read(1024)
                                    if not chunk:
                                        break
                                    out_file.write(chunk)
                                logger.info(f"Extracted file: {file_path.absolute()}")
                    except OSError as e:
                        logger.error(f"Failed to process entry: {info.filename}", e)
                        return False
            return True
        except Exception as e:
            logger.error(f"Failed to extract files from zip: {self.zip_file_path.absolute()}", e)
            return False
        finally:
            if 'zip_file' in locals() and zip_file:
                zip_file.close()

    def extract_file(self, file_name, output_dir):
        output_dir_path = Path(output_dir)
        file_path = output_dir_path / file_name
        try:
            zip_file = self.read_zip_file()
            if zip_file is None:
                return False

            try:
                info = zip_file.getinfo(file_name)
            except KeyError:
                logger.warning(f"File not found in zip: {file_name}")
                return False

            parent_dir = file_path.parent
            if not parent_dir.exists():
                try:
                    parent_dir.mkdir(parents=True, exist_ok=True)
                    logger.info(f"Created parent directory: {parent_dir.absolute()}")
                except OSError as e:
                    logger.error(f"Failed to create parent directory: {parent_dir.absolute()}", e)
                    return False

            with zip_file.open(info) as in_file:
                with open(file_path, 'wb') as out_file:
                    while True:
                        chunk = in_file.read(1024)
                        if not chunk:
                            break
                        out_file.write(chunk)
            logger.info(f"Extracted file: {file_path.absolute()}")
            return True
        except Exception as e:
            logger.error(f"Failed to extract file: {file_name}", e)
            return False
        finally:
            if 'zip_file' in locals() and zip_file:
                zip_file.close()