import sys
import logging
from logging.config import dictConfig

DEBUG = False

logging_config = dict(
    version=1,
    formatters={
        'default': {'format':
                    '%(asctime)s %(levelname)-8s '
                    '%(name)s.%(funcName)s:%(lineno)-5d %(message)s'}
    },
    handlers={
        'console': {'class': 'logging.StreamHandler',
                    'formatter': 'default',
                    'stream': sys.stderr}
    },
    loggers={
        'root': {'handlers': ['console'],
                 'level': logging.DEBUG if DEBUG else logging.INFO, }
    },
    root={
        'handlers': ['console'],
        'level': logging.DEBUG if DEBUG else logging.INFO
    }
)

logging.captureWarnings(True)
dictConfig(logging_config)
