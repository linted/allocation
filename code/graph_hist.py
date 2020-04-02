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
    parser.add_argument("-t", "--title", help="Title for the graph")
    parser.add_argument('-f',"--filter", help="filter to select results from graph", default=['.*'], nargs="*")
    parser.add_argument('-s',"--server", help="orca server url", default="http://localhost:9091")
    # parser.add_argument('-g',"--groups", help="list of args", nargs='+', default=['.*'])
    parser.add_argument('-o',"--output", help="output file for the graph")
    args = parser.parse_args()

    raw_dataFrame = None
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
        data = data['mean' == data.aggregate_name][['name',measurement]].rename(columns={measurement:data_set_name})
        if raw_dataFrame is None:
            raw_dataFrame = data
        else:
            raw_dataFrame = raw_dataFrame.merge(data, on="name")
    
    # print(raw_dataFrame.name)
    dataFrame = pd.DataFrame(columns=raw_dataFrame.columns)
    for filters in args.filter:
        dataFrame = dataFrame.merge(raw_dataFrame[raw_dataFrame.name.str.contains(filters)], how="outer")

    # print(dataFrame['name'].str.extract(r"do_([\w_]*)(?:/threads:(\d))?_mean").dropna(axis=1)[0])
    figure = go.Figure(
        data=go.Heatmap(
            z=dataFrame[dataFrame.columns.difference(['name'])],
            x=dataFrame.columns.difference(['name']),
            y=dataFrame['name'].str.extract(r"do_([\w_]*)(?:/threads:(\d))?_mean").dropna(axis=1).agg(':'.join, axis=1).str.replace("_", " ", regex=False),
            reversescale=(measurement == 'cpu_time'),
            # colorscale='Viridis'
        )
    )

    figure.update_layout(
        title={
            'text': args.title,
            'x':0.5,
            'xanchor': 'center',
            'yanchor': 'top'
        },
        # yaxis={"ticksuffix": ""}
    )

    if args.output == None:
        figure.show()
    else:
        orca.config.server_url = args.server
        figure.write_image(args.output, scale=2, width=840, height=600)
    

if __name__ == "__main__":
    main()