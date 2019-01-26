from bs4 import BeautifulSoup as bs
import requests


def make_soup(address):
    req = requests.get(address)
    req.raise_for_status()
    return bs(req.text, 'lxml')


def make_list(address, base_link):
    soup = make_soup(address)
    categories = soup.find_all("div", {"class": "mw-category-group"})
    with open("all_tasks.md", 'w') as md_file:
        md_file.writelines("# All programming tasks from rosettacode.org\n")
        for category in categories:
            md_file.writelines("## {}\n".format(category.find("h3").string))
            links = category.find_all("a")
            for link in range(len(links)):
                cur_link = links[link]
                md_file.writelines("{} [{}]({})\n\n".format(
                    link + 1, cur_link.string,
                    base_link + cur_link.get("href")))


if __name__ == "__main__":
    make_list("https://rosettacode.org/wiki/Category:Programming_Tasks",
              "https://rosettacode.org")
