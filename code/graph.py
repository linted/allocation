#!/usr/bin/env python3
import pandas as pd
# import plotly.express as px
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from plotly.io import orca
import json
import argparse
from math import ceil
from os.path import basename

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

    plot_title = ' '.join(x.capitalize() for x in results['context']['executable'].lstrip('./').split("_")) + " using " + basename(args.results_file).split("_")[1]
    # debug = results['context']['library_build_type'] != 'release'
    # scaling_enabled = results['context']['cpu_scaling_enabled']
    yaxis = 'bytes_per_second' if results['benchmarks'][0].get("bytes_per_second", False) else 'cpu_time'

    raw_data = pd.DataFrame(results['benchmarks']).dropna(subset=['aggregate_name'])
    raw_data = raw_data['mean' == raw_data.aggregate_name]
    figure = make_subplots(rows=ceil(len(args.groups)/2), cols=2 if len(args.groups) > 1 else 1)

    for group in range(len(args.groups)):
        data = raw_data[raw_data['name'].str.contains(args.groups[group])]
        # fig = px.bar(data, y="run_name", x=yaxis, orientation='h')
        # fig.show()
        figure.append_trace(
            go.Bar(
                y=data.run_name.str.extract(r"do_([\w_]*)(?:_{})(?:/threads:(\d))?".format(args.groups[group])).dropna(axis=1).agg(':'.join, axis=1), 
                x=data[yaxis], 
                orientation='h', 
                name=args.groups[group],
                text=data[yaxis].round(2),
                textposition='auto',
            ),
            1+(group//2), 
            1+(group%2)
        )
    figure.update_layout(
        title={
            'text': plot_title,
            # 'y':0.9,
            'x':0.5,
            'xanchor': 'center',
            'yanchor': 'top'
        }
    )

    if args.output == None:
        figure.show()
    else:
        orca.config.server_url = args.server
        figure.write_image(args.output)
            

if __name__ == "__main__":
    main()