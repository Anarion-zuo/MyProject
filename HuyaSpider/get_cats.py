from urllib import request
from urllib import error
from pyquery import PyQuery as pq
import pysnooper

@pysnooper.snoop()
def get_cats():
    cat_url = "https://www.huya.com/g"
    req = request.Request(cat_url)
    html = None
    try:
        response = request.urlopen(req)
        html = response.read().decode('utf-8')

    except error.URLError as e:
        print(e.reason)

    if html is None:
        exit(1)

    doc = pq(html)

    lis = doc(".game-list-item a")
    dic = dict()
    for li in lis.items():
        url = li.attr.href
        name = li('h3').text()
        dic[name] = url
    print(dic)

get_cats()