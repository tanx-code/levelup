import json

from . import app


class TestClient(object):
    def __init__(self, app):
        self.app = app
        self.app.test = True
        self.test_client = app.test_client()

    def post_json(self, endpoint, data):
        res = self.test_client.post(endpoint, data=json.dumps(
            data), content_type='application/json')
        if res.status_code != 200:
            raise Exception('Error in %s: resp:%s' % endpoint, res)
        return json.loads(res.data)


test_client = TestClient(app)
