# coding=utf-8
import json
import logging
import flask_login
from flask import Flask, request, redirect, url_for
from chatbot.core import Core

brain = Core()
app = Flask(__name__)
app.secret_key = 'whatisthat'
login_manager = flask_login.LoginManager()
login_manager.init_app(app)
with open('user_db.json', 'r', encoding='utf-8') as f:
    users = json.loads(f.read())
logger = logging.getLogger(__name__)


@app.route('/')
def index():
    return 'Hello World!'


@app.route('/ask')
def ask():
    return json.dumps({
        'reply': brain.ask(request.args['asking'])
    }, ensure_ascii=False).encode('utf8')


# User login and logout
class User(flask_login.UserMixin):
    def __init__(self, name):
        super().__init__()
        self.id = name


# 加载用户，一般用来检查用户是否存在
@login_manager.user_loader
def user_loader(name):
    if name not in users:
        return
    return User(name)


@app.route('/login', methods=['POST'])
def login():
    req = request.get_json()
    name = req['name']
    pw = req['pw']
    if users.get(name) and (pw == users[name]):
        user = User(name)
        flask_login.login_user(user)
        return redirect(url_for('protected'))
    return 'Bad'


@app.route('/logout')
@flask_login.login_required
def logout():
    current_user = flask_login.current_user.id
    logger.info('Logout: username is %s', current_user)
    flask_login.logout_user()
    return 'Successed logout '


@app.route('/protected')
@flask_login.login_required
def protected():
    # return 'Logged in as: ' + flask_login.current_user.id
    return 'Success'


@app.route('/register', methods=['POST'])
def register():
    req = request.get_json()
    name = req['name']
    pw = req['pw']
    if name in users:
        return 'Bad'
    with open('user_db.json', 'w+', encoding='utf-8') as f:
        users[name] = pw
        f.write(json.dumps(users))
    return 'Success'


@app.route('/trainning', methods=['POST'])
def trainning():
    request_json = request.get_json()
    if request_json:
        brain.trainning_request(request_json)
        return 'Success'
    else:
        return "Bad"
