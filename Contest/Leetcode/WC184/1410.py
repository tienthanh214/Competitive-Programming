import re

class Solution:
    def entityParser(self, text: str) -> str:
        spec = ["&quot;", "&apos;", "&amp;", "&gt;", "&lt;", "&frasl;"]
        rep  = ["\"", "'", "&", ">", "<", "/"]
        for i in range(len(spec)):
            text = re.sub(spec[i], rep[i], text)
        return text