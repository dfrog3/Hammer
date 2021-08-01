import json

profile1 = {

    "name":              "Enter",
    "strikeDisplay":     "#",

    "strikeChars":       [],
    "strikeSpecialKeys": ["enter"],
    "thumbDisplay":      "T",
    "thumbChars":        [],
    "thumbSpecialKeys":  ["tab"]

    }
profile2 = {

    "name":              "Copy",
    "strikeDisplay":     "V",

    "strikeChars":       ["v"],
    "strikeSpecialKeys": ["apple"],
    "thumbDisplay":      "X",
    "thumbChars":        ["x"],
    "thumbSpecialKeys":  ["apple"]

    }
profile3 = {

    "name":              "Quit",
    "strikeDisplay":     "Q",

    "strikeChars":       ["q"],
    "strikeSpecialKeys": ["apple"],
    "thumbDisplay":      "T",
    "thumbChars":        [],
    "thumbSpecialKeys":  ["apple", "tab"]

    }
profile4 = {

    "name":              "Force",
    "strikeDisplay":     "Q",

    "strikeChars":       [],
    "strikeSpecialKeys": ["apple", "option", "esc"],
    "thumbDisplay":      "#",
    "thumbChars":        [],
    "thumbSpecialKeys":  ["enter"]

    }
profile5 = {

    "name":              "Formt",
    "strikeDisplay":     "S",

    "strikeChars":       ["s"],
    "strikeSpecialKeys": ["apple", "shift"],
    "thumbDisplay":      "S",
    "thumbChars":        ["s"],
    "thumbSpecialKeys":  ["apple"]

    }
profile6 = {

    "name":              "blank",
    "strikeDisplay":     "A",

    "strikeChars":       ["a"],
    "strikeSpecialKeys": [],
    "thumbDisplay":      "B",
    "thumbChars":        ["b"],
    "thumbSpecialKeys":  []

    }

f = open("settings.json", "w")
json.dump([profile1, profile2, profile3, profile4, profile5, profile6], f, indent=4)
f.close()
