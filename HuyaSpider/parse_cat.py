from urllib import request
from urllib import error
from pyquery import PyQuery as pq
import json
import pysnooper
import re

@pysnooper.snoop()
def parse_cat(page):
    cat_url = "https://www.huya.com/cache.php?m=LiveList&do=getLiveListByPage&gameId=1&tagAll=0&page=" + str(page)
    req = request.Request(cat_url)
    doc = None
    try:
        response = request.urlopen(req)
        doc = response.read().decode('utf-8')
        # print(doc)
    except error.URLError as e:
        print(e.reason)

    if doc is None:
        exit(1)

    dic = json.loads(doc)['data']
    total_page = dic['totalPage']
    total_count = dic['totalCount']
    data_list = dic['datas']
    print(data_list[0])
    for room in data_list:
        id = room['profileRoom']
        print(id)

parse_cat(15)