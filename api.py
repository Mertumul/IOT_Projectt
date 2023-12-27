import uvicorn
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse, PlainTextResponse, JSONResponse
from telegram import send_telegram_message
from weather import get_weather_data
from firebase import get_city_name, get_message

app = FastAPI()

@app.get("/send_telegram_message_sau", response_class=HTMLResponse)
async def send_message(request: Request) -> JSONResponse:
    try:
        message = get_message().replace('"', '')
        chat_id = ""
        bot_token = ""
        await send_telegram_message(message, chat_id, bot_token)
        return JSONResponse(content={"message": "Telegram message sent successfully"}, status_code=200)
    except Exception as e:
        return JSONResponse(content={"message": f"Error: {str(e)}"}, status_code=500)
    
@app.get("/get_weather_info", response_class=PlainTextResponse)
async def get_weather_info(request: Request) -> PlainTextResponse:
    try:
        city = get_city_name().replace('"', '')
        
        openweather_api_key = ""
        weather_description, temp_celcius = await get_weather_data(openweather_api_key, city)
        print(f"{weather_description} {temp_celcius}")
        return PlainTextResponse(content=f"{weather_description} {temp_celcius}", status_code=200)
    except Exception as e:
        return JSONResponse(content={"message": f"Error: {str(e)}"}, status_code=500)    


if __name__ == "__main__":
    uvicorn.run(app, host="127.0.0.1", port=8000)
