#!/usr/bin/env python3
import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from plotly.io import orca
import argparse
import json
import re
from os import path
import numpy as np


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("results_files", help="google benchmark results json output", nargs='+')
    parser.add_argument('-f',"--filter", help="filter to remove results from graph", default='.*')
    parser.add_argument('-s',"--server", help="orca server url", default="http://localhost:9091")
    # parser.add_argument('-g',"--groups", help="list of args", nargs='+', default=['.*'])
    parser.add_argument('-o',"--output", help="output file for the graph")
    args = parser.parse_args()

    dataFrame = None
    measurement = None

    for files in args.results_files:
        with open(files, 'r') as fin:
            raw_data = json.load(fin)

        matches = re.search(r".*(lib.*\.so(?:\.\d+)?).*",path.basename(files))
        if matches:
            data_set_name = matches[1]
        else:
            data_set_name = path.basename(files).split("_")[1]
            if data_set_name.endswith(".json"):
                data_set_name = data_set_name[:-5]

        if measurement is None:
            measurement = 'bytes_per_second' if raw_data['benchmarks'][0].get("bytes_per_second", False) else 'cpu_time'
        
        data = pd.DataFrame(raw_data["benchmarks"]).dropna(subset=['aggregate_name'])
        for items in args.filter:
            data = data[items != data.name]
        data = data['mean' == data.aggregate_name][['name',measurement]].rename(columns={measurement:data_set_name})
        if dataFrame is None:
            dataFrame = data
        else:
            dataFrame = dataFrame.merge(data, on="name")

    # print(dataFrame['name'].str.extract(r"do_([\w_]*)(?:/threads:(\d))?_mean").dropna(axis=1)[0])
    figure = go.Figure(
        data=go.Heatmap(
            z=dataFrame[dataFrame.columns.difference(['name'])],
            x=dataFrame.columns.difference(['name']),
            y=dataFrame['name'].str.extract(r"do_([\w_]*)(?:/threads:(\d))?_mean").dropna(axis=1).agg(':'.join, axis=1),
            reversescale=(measurement == 'cpu_time')
            # colorscale='Viridis'
        )
    )

    if args.output == None:
        figure.show()
    else:
        orca.config.server_url = args.server
        figure.write_image(args.output)
    

if __name__ == "__main__":
    main()