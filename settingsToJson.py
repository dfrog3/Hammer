import json

profile1 = {

    "name":              "one",
    "strikeDisplay":     "a",


    "strikeChars":       ["a"],
    "strikeSpecialKeys": ["apple", "shift", "control", "option"],
    "thumbDisplay":      "b",
    "thumbChars":        ["b"],
    "thumbSpecialKeys":  []

    }
profile2 = {

    "name":              "two",
    "strikeDisplay":     "c",


    "strikeChars":       ["d"],
    "strikeSpecialKeys": ["apple", "shift"],
    "thumbDisplay":      "b",
    "thumbChars":        ["b"],
    "thumbSpecialKeys":  [ "control", "option"]

    }
profile3 = {

    "name":              "one",
    "strikeDisplay":     "a",


    "strikeChars":       ["a"],
    "strikeSpecialKeys": ["apple", "shift", "control", "option"],
    "thumbDisplay":      "b",
    "thumbChars":        ["b"],
    "thumbSpecialKeys":  []

    }
profile4 = {

    "name":              "one",
    "strikeDisplay":     "a",


    "strikeChars":       ["a"],
    "strikeSpecialKeys": ["apple", "shift", "control", "option"],
    "thumbDisplay":      "b",
    "thumbChars":        ["b"],
    "thumbSpecialKeys":  []

    }
profile5 = {

    "name":              "one",
    "strikeDisplay":     "a",


    "strikeChars":       ["a"],
    "strikeSpecialKeys": ["apple", "shift", "control", "option"],
    "thumbDisplay":      "b",
    "thumbChars":        ["b"],
    "thumbSpecialKeys":  []

    }
profile6 = {

    "name":              "one",
    "strikeDisplay":     "a",


    "strikeChars":       ["a"],
    "strikeSpecialKeys": ["apple", "shift", "control", "option"],
    "thumbDisplay":      "b",
    "thumbChars":        ["b"],
    "thumbSpecialKeys":  []

    }

f = open("settings.json", "w")
json.dump([profile1,profile2,profile3,profile4,profile5,profile6], f, indent=4)
f.close()
