import urllib.parse
import aiohttp

async def send_telegram_message(message, chat_id, bot_token):
    message_encoded = urllib.parse.quote(message)
    url = f"https://api.telegram.org/bot{bot_token}/sendMessage?chat_id={chat_id}&text={message_encoded}"

    async with aiohttp.ClientSession() as session:
        async with session.get(url) as response:
            if response.status == 200:
                print("Mesaj başariyla gönderildi.")
            else:
                print(f"İstekte bir hata oluştu. Hata kodu: {response.status}")
