import firebase_admin
from firebase_admin import db,credentials
cred = credentials.Certificate("credentials.json")
firebase_admin.initialize_app(cred, {"databaseURL": ""})

def get_city_name():
    address = db.reference("/BulutFirebase/Address")
    return address.get()


def get_message():
    message = db.reference("/BulutFirebase/Message")
    return message.get()

