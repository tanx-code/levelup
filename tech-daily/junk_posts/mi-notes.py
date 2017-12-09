# coding=utf-8
import json
import os
import re
import subprocess

DIR_TO_IMPORT = 'notes'


def save_file(file_name, date, content):
    # file name
    file_name = os.path.join(DIR_TO_IMPORT, file_name)

    # content
    content = '\n'.join([d.strip() for d in content.split('\n')[1:]])

    # 2001年2月10日 10:00 to  2/10/2001 10:00
    date = re.findall(r'\d+', date)
    year, month, day, time = date[0], date[1], date[2], ':'.join(date[3:])
    date = month + '/' + day + '/' + year + ' ' + time

    # save
    with open(file_name, 'w+', encoding='utf8') as fp:
        fp.write(content)

    # set file's creation time
    # SetFile -d '12/31/1999 23:59[:59]' file.txt
    print(subprocess.check_output(['SetFile', '-d', date, file_name]))
    print(subprocess.check_output(['SetFile', '-m', date, file_name]))
    print('Done. ', file_name)


def mkdir(path, prefix=DIR_TO_IMPORT):
    if not os.path.exists(os.path.join(prefix, path)):
        os.makedirs(os.path.join(prefix, path))


def parse_items(items, box):
    for d in items:
        date = d['created_time']
        content = d['content']
        save_file(os.path.join(box, date), date, content)


def run():
    mkdir(DIR_TO_IMPORT, '')
    with open('data.json', mode='r', encoding='utf8') as fp:
        data = json.loads(fp.read())
        singles = []
        for item in data:
            if item.get('box_name'):
                mkdir(item['box_name'])
                parse_items(item['content'], item['box_name'])
            else:
                singles.append(item)
        parse_items(singles, '')


if __name__ == '__main__':
    run()
