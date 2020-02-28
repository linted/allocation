#!/usr/bin/env python3
import numpy as np
from matplotlib import pyplot
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
    args = parser.parse_args()

    # print(dir(args))
    with open(args.results_file, 'r') as fin:
        results = json.load(fin)

    prog_name = results['context']['executable']
    debug = results['context']['library_build_type'] != 'release'
    scaling_enabled = results['context']['cpu_scaling_enabled']

    groups = {x:{} for x in args.groups}

    # filter results
    for test in results['benchmarks']:
        if test['run_type'] == "aggregate":
            for pattern in args.groups:
                if re.search(pattern, test['run_name']):
                    if not groups[pattern].get(test['run_name'], False):
                        groups[pattern][test['run_name']] = {
                            'mean':None, 
                            'median':None, 
                            'stddev':None,
                        }
                    groups[pattern][test['run_name']][test['aggregate_name']] = test.get("bytes_per_second", test.get("cpu_time", None))
                    break


    # graph results
    for groupNum in range(len(args.groups)):
        graph_elements = groups[args.groups[groupNum]]
        # print("{}:{}".format(args.groups[groupNum],graph_elements[args.groups[groupNum]]))

        if len(graph_elements) == 0:
            continue

        y_ticks = np.arange(len(graph_elements))

        # and now plot everythin
        pyplot.subplot(ceil(len(args.groups)/2), 2, groupNum+1)

        pyplot.barh(y_ticks,
            [x['mean'] for x in graph_elements.values()], 
            xerr=[x['stddev'] for x in graph_elements.values()])

        ylabels = ['-'.join(x.split('_')[1:-1]) + ((':' + x.split(':')[-1]) if ':' in x else '') for x in graph_elements.keys()]

        pyplot.yticks(y_ticks, labels=ylabels)

        xAxis = "Bytes per second" if results['benchmarks'][0].get("bytes_per_second", False) else "time in {}".format(results['benchmarks'][0]['time_unit'])
        pyplot.xlabel(xAxis)

        if len(args.groups) == 1:
            pyplot.title(prog_name)
        else:
            pyplot.title(args.groups[groupNum])

        if debug:
            pyplot.text(0.95, 0.05, 'DEBUG',
                fontsize=50, color='gray',
                ha='center', va='bottom', alpha=0.5, rotation=20)
        if scaling_enabled:
            pyplot.text(0.05, 0.95, 'SCALED',
                fontsize=50, color='gray',
                ha='center', va='top', alpha=0.5, rotation=20)

    title = path.basename(args.results_file).replace("_", " ")
    pyplot.suptitle(title if title[-5:] != '.json' else title[:-5], va="center")

    pyplot.tight_layout()
    if args.output:
        pyplot.savefig(args.output, dpi=300)
    else:
        pyplot.show()

if __name__ == "__main__":
    main()