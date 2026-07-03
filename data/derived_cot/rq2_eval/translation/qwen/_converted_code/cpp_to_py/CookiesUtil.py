import json
import os

class CookiesUtil:
    def __init__(self, cookies_file):
        self.cookies_file = cookies_file
        self.cookies = {}  # Dictionary to store cookies

    def get_cookies(self, response):
        """Extract cookies from the response and save them."""
        if 'cookies' in response:
            # Convert the response cookies (dict) to our internal structure
            self.cookies = response['cookies']
            self._save_cookies()

    def load_cookies(self):
        """Load cookies from the file and return them as a dictionary."""
        cookies_data = {}
        try:
            if os.path.exists(self.cookies_file):
                with open(self.cookies_file, 'r') as file:
                    cookies_data = json.load(file)
        except Exception as e:
            print(f"Error reading JSON file: {e}")
        return cookies_data

    def _save_cookies(self):
        """Save cookies to the file, ensuring proper JSON format."""
        try:
            with open(self.cookies_file, 'w') as file:
                json.dump(self.cookies, file, indent=4)
            return True
        except Exception as e:
            print(f"Error writing JSON file: {e}")
            return False

    def set_cookies(self, request):
        """Format cookies for the request."""
        if not self.cookies:
            return
        # Build the cookies string in the format "key1=value1; key2=value2"
        cookie_str = '; '.join([f"{key}={value}" for key, value in self.cookies.items()])
        request['cookies'] = cookie_str