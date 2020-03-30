#!/usr/bin/env python3
import pandas as pd
# import plotly.express as px
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from plotly.io import orca
import json
import argparse
import re
from math import ceil
from os import path

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("results_file", help="google benchmark results json output")
    parser.add_argument('-g',"--groups", help="list of args", nargs='+', default=['.*'])
    parser.add_argument('-o',"--output", help="output file for the graph")
    parser.add_argument('-s',"--server", help="orca server url", default="http://localhost:9091")
    args = parser.parse_args()

    # print(dir(args))
    with open(args.results_file, 'r') as fin:
        results = json.load(fin)

    # prog_name = results['context']['executable']
    # debug = results['context']['library_build_type'] != 'release'
    # scaling_enabled = results['context']['cpu_scaling_enabled']
    yaxis = 'bytes_per_second' if results['benchmarks'][0].get("bytes_per_second", False) else 'cpu_time'

    raw_data = pd.DataFrame(results['benchmarks']).dropna(subset=['aggregate_name'])

    figure = make_subplots(rows=ceil(len(args.groups)/2), cols=2 if len(args.groups) > 1 else 1)

    for group in range(len(args.groups)):
        data = raw_data[raw_data['name'].str.contains(args.groups[group])]
        # fig = px.bar(data, y="run_name", x=yaxis, orientation='h')
        # fig.show()
        figure.append_trace(go.Bar(y=data.run_name, x=data[yaxis], orientation='h', name=args.groups[group]), 1+(group//2), 1+(group%2))
        
    if args.output == None:
        figure.show()
    else:
        orca.config.server_url = args.server
        figure.write_image(args.output)
            

if __name__ == "__main__":
    main()