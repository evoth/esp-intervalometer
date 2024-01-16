import re
from os.path import join

dist_path = "client/dist"
resources_cpp_path = "intervalometer/src/resources.cpp"

# Reads contents of index.html
with open(join(dist_path, "index.html"), "r") as f:
    html = f.read()

# Replaces each matching script tag with in inline script tag by retrieving the
# contents of the corresponding files and inserting them into the html text
regex = r'<script type="module" crossorigin src="\/(.*\.js)"><\/script>'
matches = re.finditer(regex, html)
for match in matches:
    with open(join(dist_path, match.group(1)), "r") as f:
        js = f.read().strip()
    html = html.replace(match.group(0), f'<script type="module">{js}</script>', 1)

# Does the same as above, but with CSS files and style tags
regex = r'<link rel="stylesheet" crossorigin href="\/(.*\.css)">'
matches = re.finditer(regex, html)
for match in matches:
    with open(join(dist_path, match.group(1)), "r") as f:
        css = f.read().strip()
    html = html.replace(match.group(0), f"<style>{css}</style>", 1)

# Reads contents of resources.cpp
with open(resources_cpp_path, "r") as f:
    cpp = f.read()

# Replaces the indexHtml literal contents in resources.cpp with updated HTML
regex = r'const char indexHtml\[\] PROGMEM = R"rawliteral\(.*?\)rawliteral";'
match = re.search(regex, cpp, re.DOTALL)
cpp = cpp.replace(
    match.group(0),
    f'const char indexHtml[] PROGMEM = R"rawliteral(\n{html.strip()}\n)rawliteral";',
    1,
)

# Writes contents of resources.cpp
with open(resources_cpp_path, "w") as f:
    f.write(cpp)
