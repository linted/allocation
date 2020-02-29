#!/usr/bin/env python3
import matplotlib.pyplot as plt
from matplotlib import colors
import argparse
import json
import re
from os import path
import numpy as np


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("results_files", help="google benchmark results json output", nargs='+')
    parser.add_argument('-f',"--filter", help="filter to remove results from graph", default='.*')
    # parser.add_argument('-g',"--groups", help="list of args", nargs='+', default=['.*'])
    parser.add_argument('-o',"--output", help="output file for the graph")
    args = parser.parse_args()

    data = {}

    xCoordinates = []
    yCoordinates = []
    weights = []
    ylabels = []
    xlabels = []
    plot_title = 'Completion time'

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

        
        xlabels.append(data_set_name)

        for test in raw_data['benchmarks']:
            if test['run_type'] == "aggregate":
                if re.search(args.filter, test['run_name']):
                    if not data.get(test['run_name'], False):
                        data[test['run_name']] = {}
                    if not data[test['run_name']].get(files, False):
                        data[test['run_name']][files] = {
                            'mean':None, 
                            'median':None, 
                            'stddev':None,
                        }
                    if test.get("bytes_per_second",False) is not False:
                        data[test['run_name']][files][test['aggregate_name']] = test["bytes_per_second"]
                        plot_title = "Bytes per second"
                    else:
                        data[test['run_name']][files][test['aggregate_name']] = -test.get("cpu_time", None)

    # print(data)

    for test in zip(data, range(len(data))):
        test_name = ' '.join(test[0].rsplit('/')[0].split('_')[1:]) + ((':' + test[0].split(':')[-1]) if ':' in test[0] else '')

        ylabels.append(test_name)
        for fileNum in range(len(args.results_files)):
            xCoordinates.append(fileNum)
            yCoordinates.append(test[1])
            weights.append(data[test[0]][args.results_files[fileNum]]['mean'])


    fig, ax = plt.subplots()
    ax.hist2d(
        xCoordinates,
        yCoordinates,
        weights=weights,
        cmap='plasma',
        bins=(
            np.arange(len(args.results_files)+1)-0.5, 
            np.arange(len(data)+1)-0.5
        )
    )

    print(len(data))

    ax.set_xticks(np.arange(len(xlabels)))
    ax.set_xticklabels(xlabels, rotation=20, fontsize=5)
    ax.set_yticks(np.arange(len(ylabels)))
    ax.set_yticklabels(ylabels, fontsize=5)

    ax.set_xlabel('Library', fontsize=10)
    ax.set_ylabel('Test', fontsize=10)
    ax.set_title(plot_title)

    fig.tight_layout()
    if args.output:
        plt.savefig(args.output, dpi=300)
    else:
        plt.show()
    

if __name__ == "__main__":
    main()