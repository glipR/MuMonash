import xml.etree.ElementTree as ET
from collections import Counter
import sys
from decimal import Decimal

sys.setrecursionlimit(20000)

n_words = 0

def _assert(cond):
    if cond:
        pass
    else:
        import sys
        sys.exit(1)

def token_to_word(token):
    token = token.lower()
    for c in ["<", ">", "/", "\\"]:
        if c in token:
            import sys
            sys.exit(1)
            
    for c in [",", ".", "?", "!"]:
        while c in token:
            token = token.replace(c, "")
    return token

def line_to_words(line):
    maybe_stops = list(map(token_to_word, line.strip().split()))
    long_tokens = [w for w in maybe_stops if w not in stop_words]
    words = [w for w in long_tokens if len(w) >= 4]
    return words

stop_words = input().strip().split(';')
index_terms = input().strip().split(';')

raw_xml_doc = ""
line = input()
while line is not None:
    raw_xml_doc += " " + line.replace("\n", " ") + " "
    
    try:
        line = input()
    except EOFError:
        break

tree = ET.fromstring(f'<root> {raw_xml_doc} </root>')

def count_element(element, weight=0):
    global n_words
    
    if element.tag == "title":
        _assert(weight == 0)
        weight = 5
    elif element.tag == "abstract":
        _assert(weight == 0)
        weight = 3
    elif element.tag == "body":
        _assert(weight == 0)
        weight = 1
    
    words = []
    raw_text = (element.text or "") + (element.tail or "")
    if raw_text != "":
        words = line_to_words(raw_text)
        if weight > 0:
            n_words += len(words)
    c = Counter(words*weight)
    
    # print(element.tag, weight, words, c)
    
    for child in element:
        c += count_element(child, weight=weight)

    return c

all_words = count_element(tree)

# print(f'n_words={n_words}')

# print(index_terms)

densities = [(-all_words[w], w) for w in index_terms if all_words[w]>0]
n_printed = 0
last_count = None

# print(densities)
# print(all_words)

for count, w in sorted(densities):
    count = -count
    if last_count is None or last_count == count or n_printed < 3:
        d = str(Decimal(100) * Decimal(count) / Decimal(n_words))
        print(f"{w}: {d}")
        last_count = count
        n_printed += 1

