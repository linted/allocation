#!/usr/bin/env python3
import argparse
import json
import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from plotly.io import orca
from os import path
import re
from math import ceil

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("results_files", help="google benchmark results json output", nargs='+')
    parser.add_argument('-f',"--filter", help="filter to select results from graph", default=['.*'], nargs="*")
    parser.add_argument('-o',"--output", help="output file for the graph")
    parser.add_argument('-s',"--server", help="orca server url", default="http://localhost:9091")
    args = parser.parse_args()

    # figure = make_subplots(rows=ceil(len(args.results_files)/2), cols=2 if len(args.results_files) > 1 else 1)
    figure = go.Figure()
    measurement = None
    
    for files in range(len(args.results_files)):
        with open(args.results_files[files], 'r') as fin:
            raw_data = json.load(fin)

        matches = re.search(r".*(lib.*\.so(?:\.\d+)?).*",path.basename(args.results_files[files]))
        if matches:
            data_set_name = matches[1]
        else:
            data_set_name = path.basename(files).split("_")[1]
            if data_set_name.endswith(".json"):
                data_set_name = data_set_name[:-5]

        if measurement is None:
            measurement = 'bytes_per_second' if raw_data['benchmarks'][0].get("bytes_per_second", False) else 'cpu_time'
        
        data = pd.DataFrame(raw_data["benchmarks"]).dropna(subset=['aggregate_name'])
        data = data['mean' == data.aggregate_name][['name',measurement]]
        
        dataFrame = pd.DataFrame(columns=data.columns)
        for filters in args.filter:
            dataFrame = dataFrame.merge(data[data.name.str.contains(filters)], how="outer")

        figure.add_trace(
            go.Scatterpolar(
                r=dataFrame[measurement],
                theta=dataFrame.name,
                fill='toself'
            )
        )



    if args.output == None:
        figure.show()
    else:
        orca.config.server_url = args.server
        figure.write_image(args.output)

if __name__ == "__main__":
    main()
