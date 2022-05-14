import telebot
import subprocess
from telebot import types

TOKEN = '5226116153:AAFKqnhXZB2NgBsiLsJkwhM6bdLj2VeIc7E'

bot = telebot.TeleBot(TOKEN)

def review_0(message):
    message_to_save = message.text
    print(message_to_save)

    file = open("AB.txt", "w")
    file.write(message_to_save)
    file.close()


def review(message):
    message_to_save = message.text
    print(message_to_save)

    file = open("AB.txt", "r")
    temp = file.read()
    file.close()

    file = open("AB.txt", "w")
    file.write(temp + '\n' + message_to_save)
    file.close()

@bot.message_handler(commands=['start'])
def start(message):
    bot.send_message(message.chat.id, 'Hello, ' + message.from_user.first_name + '!')
    bot.send_message(message.chat.id, 'I am Phystech.Map_bot. I was designed to help you to find out way from one cabinet to another.')
    bot.send_message(message.chat.id,'First, determine your current location. Use command of menu: /building_from and /cabinet_from.\n'
                                     'Secondly, determine your destination. Use commands of menu: /building_to and /cabinet_to.\n'
                                     'Then use command /route to get route.\n')

@bot.message_handler(commands=['building_from'])
def start(message):
    kb = types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    btn_1 = types.KeyboardButton(text='NK')
    btn_2 = types.KeyboardButton(text='GK')
    btn_3 = types.KeyboardButton(text='LK')
    btn_4 = types.KeyboardButton(text='Figure')
    btn_5 = types.KeyboardButton(text='Arctic')
    kb.add(btn_1, btn_2, btn_3)
    kb.add(btn_4, btn_5)
    sent = bot.send_message(message.chat.id, 'What building are you in now?', reply_markup=kb)
    bot.register_next_step_handler(sent, review_0)

@bot.message_handler(commands=['cabinet_from'])
def start(message):
    sent = bot.send_message(message.chat.id, 'Which cabinet are you standing in front of?', reply_markup=types.ReplyKeyboardRemove())
    bot.register_next_step_handler(sent, review)

@bot.message_handler(commands=['building_to'])
def start(message):
    kb = types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    btn_1 = types.KeyboardButton(text='NK')
    btn_2 = types.KeyboardButton(text='GK')
    btn_3 = types.KeyboardButton(text='LK')
    btn_4 = types.KeyboardButton(text='Figure')
    btn_5 = types.KeyboardButton(text='Arctic')
    kb.add(btn_1, btn_2, btn_3)
    kb.add(btn_4, btn_5)
    sent = bot.send_message(message.chat.id, 'What building do you need to be in?', reply_markup=kb)
    bot.register_next_step_handler(sent, review)

@bot.message_handler(commands=['cabinet_to'])
def start(message):
    sent = bot.send_message(message.chat.id, 'Which cabinet do you need to be in?', reply_markup=types.ReplyKeyboardRemove())
    bot.register_next_step_handler(sent, review)

@bot.message_handler(commands=['route'])
def start(message):
    #subprocess.call('./to_Kris.sh')
    line = 'Go on left 20 metres.'
    bot.send_message(message.chat.id, line)
    file = open("AB.txt", "w")
    file.close()

bot.polling()
