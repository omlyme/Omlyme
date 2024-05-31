import requests
import json

BASE_URL: str = "https://cpmnuker.anasov.ly"

class CPMNuker:

    def __init__(self, access_key) -> None:
        self.auth_token = None
        self.access_key = access_key
        
    def login(self, email, password) -> int:
        payload = { "account_email": email, "account_password": password }
        params = { "key": self.access_key }
        response = requests.post(f"{BASE_URL}/api/account_login", params=params, data=payload)
        response_decoded = json.loads(response.text)
        if response_decoded.get("ok"):
            self.auth_token = response_decoded.get("auth")
        return response_decoded.get("error")
    
    def register(self, email, password) -> int:
        payload = { "account_email": email, "account_password": password }
        params = { "key": self.access_key }
        response = requests.post(f"{BASE_URL}/api/account_register", params=params, data=payload)
        response_decoded = json.loads(response.text)
        if response_decoded.get("ok"):
            self.auth_token = response_decoded.get("auth")
        return response_decoded.get("error")
    
    def get_player_data(self) -> any:
        payload = { "account_auth": self.auth_token }
        params = { "key": self.access_key }
        response = requests.post(f"{BASE_URL}/api/get_data", params=params, data=payload)
        response_decoded = json.loads(response.text)
        return response_decoded
    
    def set_player_data(self, content) -> bool:
        payload = { "account_auth": self.auth_token, "content": json.dumps(content) }
        params = { "key": self.access_key }
        response = requests.post(f"{BASE_URL}/api/set_data", params=params, data=payload)
        response_decoded = json.loads(response.text)
        return response_decoded.get("ok")
    
    def set_player_rank(self) -> bool:
        payload = { "account_auth": self.auth_token }
        params = { "key": self.access_key }
        response = requests.post(f"{BASE_URL}/api/set_rank", params=params, data=payload)
        response_decoded = json.loads(response.text)
        return response_decoded.get("ok")
    
    def get_key_data(self) -> any:
        params = { "key": self.access_key }
        response = requests.get(f"{BASE_URL}/api/get_key_data", params=params)
        response_decoded = json.loads(response.text)
        return response_decoded
    
    def delete(self) -> None:
        payload = { "account_auth": self.auth_token }
        params = { "key": self.access_key }
        response = requests.post(f"{BASE_URL}/api/account_delete", params=params, data=payload)
        response_decoded = json.loads(response.text)
        



"""
match login_response:
    case 0:
        print("SUCCESSFUL.")
        sleep(1)
    case 100:
        print("EMAIL NOT FOUND.")
        sleep(1)
        continue
    case 101:
        print("INVALID PASSWORD.")
        sleep(1)
        continue
    case 102:
        print("INSUFFICIENT FUNDS.")
        sleep(1)
        continue
    case 103:
        print("INVALID ACCESS KEY.")
        sleep(1)
        continue
    case 104:
        print("MISSING PARAMETERS.")
        sleep(1)
        continue
    case 105:
        print("EMAIL EXISTS.")
        sleep(1)
        continue
    case 106:
        print("MISSING_PASSWORD.")
        sleep(1)
        continue
    case 107:
        print("INVALID_EMAIL.")
        sleep(1)
        continue
    case 108:
        print("MISSING_EMAIL.")
        sleep(1)
        continue
    case 109:
        print("ACCESS_KEY_BLOCKED.")
        sleep(1)
        continue
    case 404:
        print("UNKNOWN_ERROR.")
        sleep(1)
        continue
"""