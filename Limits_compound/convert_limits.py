import csv
import json

Limits = {"YSlice": {}, "XSlice": {}}
with open('run2_limits.csv', newline='') as file:
    reader = csv.reader(file)
    for row in reader:
        #print(row)    # each row is a list of values
        MX = int(float(row[0]))
        MY = int(float(row[1]))
        if MY not in Limits["YSlice"]:
            Limits["YSlice"][MY] = {}
        if MX not in Limits["XSlice"]:
            Limits["XSlice"][MX] = {}
        obs = float(row[2])
        limit = [obs, obs, obs, obs, obs]
        Limits["YSlice"][MY][MX] = limit
        Limits["XSlice"][MX][MY] = limit
print(Limits)
with open("limits_database/Limits_run2_observed.txt", "w") as f:
    json.dump(Limits, f, indent = 4)
