from dictionaries.script_save_to_db import run
from api import app

from flask_script import Manager


manager = Manager(app)

@manager.command
def fill_mongodb():
    run()

if __name__ == '__main__':
    manager.run()
