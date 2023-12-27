import aiohttp
async def kelvin_to_celcius(kelvin):
    celcius = kelvin - 273.15
    return celcius

async def get_weather_data(api_key, city):
    url = f"http://api.openweathermap.org/data/2.5/weather?appid={api_key}&q={city}"
    
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as response:
            data = await response.json()

    temp_kelvin = data['main']['temp']
    temp_celcius = round(await kelvin_to_celcius(temp_kelvin), 1)
    weather_description = data['weather'][0]['description']

    return weather_description, temp_celcius
