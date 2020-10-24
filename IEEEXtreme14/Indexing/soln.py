import xml.etree.ElementTree as ET
from collections import Counter

n_words = 0

def token_to_word(token):
    token = token.lower()
    for c in [",", ".", "?", "!"]:
        while c in token:
            token = token.replace(c, "")
    return token

def line_to_words(line):
    mostly_words = list(map(token_to_word, line.strip().split()))
    ehh = [w for w in mostly_words if w not in stop_words]
    words = [w for w in ehh if len(w) >= 4]
    return words

stop_words = input().strip().split(';')
index_terms = input().strip().split(';')

raw_xml_doc = ""
line = input()
while line is not None:
    raw_xml_doc += line + " "
    
    try:
        line = input()
    except EOFError:
        break

tree = ET.fromstring(f'<root>{raw_xml_doc}</root>')

def count_element(element, weight=0):
    global n_words
    
    if element.tag == "title":
        weight = 5
    elif element.tag == "abstract":
        weight = 3
    elif element.tag == "body":
        weight = 1
    
    words = []
    if element.text is not None:
        words = line_to_words(element.text)
        if weight > 0:
            n_words += len(words)
    c = Counter(words*weight)
    
    # print(element.tag, weight, words, c)
    
    
    for child in element:
        c += count_element(child, weight=weight)

    return c

all_words = count_element(tree)

# print(f'n_words={n_words}')

densities = [(-100*all_words[w]/n_words, w) for w in index_terms]
n_printed = 0
last_d = None
for d, w in sorted(densities):
    d = -d
    if last_d is None or last_d == d or n_printed < 3:
        print(f"{w}: {d}")
        last_d = d
        n_printed += 1

