import logging
import zipfile
import io
from pathlib import Path
from typing import Optional

logger = logging.getLogger(__name__)


class ZipFileProcessor:
    def __init__(self, zip_file_name: str):
        self.zip_file_path = Path(zip_file_name)

    def read_zip_file(self) -> Optional[zipfile.ZipFile]:
        if not self.zip_file_path.exists():
            logger.error(
                f"Zip file does not exist: {self.zip_file_path.resolve()}"
            )
            return None
        try:
            return zipfile.ZipFile(str(self.zip_file_path), "r")
        except (OSError, zipfile.BadZipFile) as e:
            logger.exception(
                f"Failed to read the zip file: {self.zip_file_path.resolve()}"
            )
            return None

    def extract_all(self, output_dir: str) -> bool:
        output_dir_path = Path(output_dir)
        zip_file = self.read_zip_file()
        if zip_file is None:
            return False
        try:
            if not output_dir_path.exists():
                try:
                    output_dir_path.mkdir(parents=True, exist_ok=False)
                    logger.info(
                        f"Created output directory: {output_dir_path.resolve()}"
                    )
                except OSError as e:
                    logger.exception(
                        f"Failed to create output directory: {output_dir_path.resolve()}"
                    )
                    return False

            for entry in zip_file.infolist():
                file_path = output_dir_path / entry.filename
                try:
                    if entry.filename.endswith("/"):
                        if not file_path.exists():
                            file_path.mkdir(parents=True, exist_ok=True)
                            logger.info(
                                f"Created directory: {file_path.resolve()}"
                            )
                    else:
                        # Write the file
                        with zip_file.open(entry, "r") as in_file, open(
                            file_path, "wb"
                        ) as out_file:
                            buffer = bytearray(1024)
                            while True:
                                n = in_file.readinto(buffer)
                                if n == 0:
                                    break
                                out_file.write(buffer[:n])
                        logger.info(
                            f"Extracted file: {file_path.resolve()}"
                        )
                except (OSError, zipfile.BadZipFile) as e:
                    logger.exception(
                        f"Failed to process entry: {entry.filename}"
                    )
            return True
        finally:
            zip_file.close()

    def extract_file(self, file_name: str, output_dir: str) -> bool:
        output_dir_path = Path(output_dir)
        file_path = output_dir_path / file_name
        zip_file = self.read_zip_file()
        if zip_file is None:
            return False
        try:
            if file_name not in zip_file.namelist():
                logger.warning(f"File not found in zip: {file_name}")
                return False

            entry = zip_file.getinfo(file_name)

            parent = file_path.parent
            if not parent.exists():
                try:
                    parent.mkdir(parents=True, exist_ok=False)
                    logger.info(
                        f"Created parent directory: {parent.resolve()}"
                    )
                except OSError as e:
                    logger.exception(
                        f"Failed to create parent directory: {parent.resolve()}"
                    )
                    return False

            with zip_file.open(entry, "r") as in_file, open(
                file_path, "wb"
            ) as out_file:
                buffer = bytearray(1024)
                while True:
                    n = in_file.readinto(buffer)
                    if n == 0:
                        break
                    out_file.write(buffer[:n])
            logger.info(f"Extracted file: {file_path.resolve()}")
            return True
        except (OSError, zipfile.BadZipFile) as e:
            logger.exception(f"Failed to extract file: {file_name}")
            return False
        finally:
            zip_file.close()