import os
import zipfile
import shutil

class ZipFileInfo:
    def __init__(self, filename="", mode=""):
        self.filename = filename
        self.mode = mode

class ZipFileProcessor:
    def __init__(self, zip_file_path):
        self.zip_file_path_ = zip_file_path

    def extract_all(self, output_directory):
        if not output_directory:
            return False
        
        if not self.create_directory_if_not_exists(output_directory):
            return False
        
        try:
            with zipfile.ZipFile(self.zip_file_path_, 'r') as zip_ref:
                for entry in zip_ref.infolist():
                    output_file_path = os.path.join(output_directory, entry.filename)
                    if entry.is_dir():
                        continue
                    parent_dir = os.path.dirname(output_file_path)
                    if parent_dir and not os.path.exists(parent_dir):
                        os.makedirs(parent_dir, exist_ok=True)
                    try:
                        with zip_ref.open(entry) as entry_file, open(output_file_path, 'wb') as out_file:
                            shutil.copyfileobj(entry_file, out_file)
                    except OSError as e:
                        print(f"Failed to open output file: {output_file_path}")
                        return False
        except Exception as e:
            print(f"Failed to open zip file: {self.zip_file_path_}")
            return False
        return True

    def extract_file(self, file_name, output_directory):
        if not output_directory:
            return False
        
        if not self.create_directory_if_not_exists(output_directory):
            print(f"Failed to create output directory: {output_directory}")
            return False
        
        try:
            with zipfile.ZipFile(self.zip_file_path_, 'r') as zip_ref:
                try:
                    zip_ref.getinfo(file_name)
                except KeyError:
                    print(f"File not found in zip: {file_name}")
                    return False
                
                output_file_path = os.path.join(output_directory, file_name)
                parent_dir = os.path.dirname(output_file_path)
                if parent_dir and not os.path.exists(parent_dir):
                    os.makedirs(parent_dir, exist_ok=True)
                
                try:
                    with zip_ref.open(file_name) as entry_file, open(output_file_path, 'wb') as out_file:
                        shutil.copyfileobj(entry_file, out_file)
                except OSError as e:
                    print(f"Failed to open output file: {output_file_path}")
                    return False
        except Exception as e:
            print(f"Failed to open zip file: {self.zip_file_path_}")
            return False
        return True

    def create_zip_file(self, files, output_zip_file):
        try:
            zipf = zipfile.ZipFile(output_zip_file, 'w', encoding='utf-8')
        except Exception as e:
            print(f"Error opening zip file: {output_zip_file}")
            return False
        
        try:
            for file_path in files:
                try:
                    zipf.write(file_path)
                except Exception as e:
                    print(f"Error adding file to zip: {file_path}")
                    try:
                        zipf.close()
                    except:
                        pass
                    return False
        finally:
            try:
                zipf.close()
            except Exception as e:
                print(f"Error closing zip file: {output_zip_file}")
                return False
        
        return True

    def read_zip_file(self):
        try:
            with zipfile.ZipFile(self.zip_file_path_, 'r') as zipf:
                return ZipFileInfo(self.zip_file_path_, 'r')
        except:
            return ZipFileInfo()

    def create_directory_if_not_exists(self, dir_path):
        if not os.path.exists(dir_path):
            try:
                os.makedirs(dir_path, exist_ok=True)
            except OSError:
                return False
        return True