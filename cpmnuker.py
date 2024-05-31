import requests
import json

# Copyright (C) Anasov <me@anasov.ly> - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Anasov <me@anasov.ly>, 05, May, 2024.

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
        