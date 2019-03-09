import requests
import sys
import json
import os

def getCredentials():
    path = os.getcwd() + "/secret"
    file = open(path, "r")
    uid = file.readline().strip()
    secret = file.readline().strip()
    return [uid, secret]


def getOauthToken():
    uid, secret = getCredentials()
    # print(uid)
    # print(secret)
    oauth_url = "https://api.intra.42.fr/oauth/token"
    data = {
        "grant_type" : "client_credentials",
        "client_id" : uid,
        "client_secret" : secret
    }
    #retry will go here   
    oauth_resp = requests.post(oauth_url, data=data).json()
    # print(oauth_resp)
    return oauth_resp["access_token"]


token = getOauthToken()
headers = {"Authorization" : "Bearer {0}".format(token)}
if (len(sys.argv) < 2):
    print("No users provided")
else:
    usernames = sys.argv[1:]
    for user in usernames:
        location = requests.get(f"https://api.intra.42.fr/v2/users/{user.strip()}/locations", headers=headers, params={"filter[active]" : "true"}).json()
        if (location):
            print(f"{user}: can be found at {location[0]['host']}")
        else:
            print(f"{user}: user not found on campus, or does not exist")