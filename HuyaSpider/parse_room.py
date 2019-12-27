from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.wait import WebDriverWait

from pyquery import PyQuery as pq

import pysnooper

@pysnooper.snoop()
def parse_room(id):
    driver = webdriver.Chrome()
    html = None
    url = "https://www.huya.com/" + id
    try:
        driver.get(url)
        # chatb = driver.find_element_by_id("tipsOrchat")
        wait = WebDriverWait(driver, 10)
        wait.until(EC.presence_of_element_located((By.ID, 'chatRoom')))
        # print(driver.page_source)
        doc = driver.page_source
        html = pq(doc)
    finally:
        driver.close()

    if html is None:
        exit(1)

    detail = html(".host-detail.J_roomHdDetail")
    title = html("#J_roomTitle").text()
    # lv = html("#J_roomHdHostLvIcon")
    name = detail(".host-name").text()
    live_count = detail("#live-count").text()
    sub_count = html("#activityCount").text()

parse_room("965777")