import json

n = int(input())
publications = json.loads(input())
pubs = {}
for pub in publications["publications"]:
    pubs[pub["publicationNumber"]] = {
        "name": pub["publicationTitle"],
        "articles": 0,
        "citations": 0,
        "articleIds": [],
    }
    for article in pub["articleCounts"]:
        if article["year"] in ["2017", "2018"]:
            pubs[pub["publicationNumber"]]["articles"] += int(article["articleCount"])

for x in range(n-1):
    article = json.loads(input())
    for citation in article["paperCitations"]["ieee"]:
        num = citation["publicationNumber"]
        if num in pubs.keys():
            if citation["year"] in ["2017", "2018"]:
               pubs[num]["citations"] += 1

names_and_factors = []

for key in pubs.keys():
    name = pubs[key]["name"]
    result = pubs[key]["citations"] / pubs[key]["articles"]
    names_and_factors.append([name, result])

names_and_factors.sort(key=lambda x: (-x[1], x[0]))
for name, factor in names_and_factors:
    print(f'{name}: {factor:.2f}')
