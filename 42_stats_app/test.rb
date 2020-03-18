require "oauth2"
UID = "ad35edd799c5bc1a96f50a6172e3f3937046c9d06ccfb3097df664f9f3027010"
SECRET = "05dd3ce962d6b2233fcdf0453a9545ae4cefa94abe0296774ca664f6011d8e6f"

client = OAuth2::Client.new(UID, SECRET, site: "https://api.intra.42.fr")
token = client.client_credentials.get_token

campus_list = token.get("/v2/campus/17/").parsed
puts campus_list
