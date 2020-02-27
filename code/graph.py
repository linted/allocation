#!/usr/bin/env python3
import numpy as np
from matplotlib import pyplot
import json
import argparse
import re
from math import ceil

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

    benchmarks = {}

    for test in results['benchmarks']:
        if test['run_type'] == "aggregate":
            if not benchmarks.get(test['run_name'], False):
                benchmarks[test['run_name']] = {
                    'mean':None, 
                    'median':None, 
                    'stddev':None,
                }
            benchmarks[test['run_name']][test['aggregate_name']] = test.get("bytes_per_second", test.get("cpu_time", None))
    

    for group in range(len(args.groups)):
        graph_elements = {}
        for key in benchmarks.keys():
            if re.search(args.groups[group], key):
                graph_elements[key] = benchmarks[key]

        y_ticks = np.arange(len(graph_elements))

        if len(graph_elements) == 0:
            continue

        # and now plot everythin
        pyplot.subplot(ceil(len(args.groups)/2), 2, group+1)
        pyplot.barh(y_ticks,
            [x['mean'] for x in graph_elements.values()], 
            xerr=[x['stddev'] for x in graph_elements.values()])

        pyplot.yticks(y_ticks, labels=['-'.join(x.split('_')[1:-1]) for x in graph_elements.keys()])

        xAxis = "Bytes per second" if results['benchmarks'][0].get("bytes_per_second", False) else "time in {}".format(results['benchmarks'][0]['time_unit'])
        pyplot.xlabel(xAxis)

        if len(args.groups) == 1:
            pyplot.title(prog_name)
        else:
            pyplot.title(args.groups[group])

        if debug:
            pyplot.text(0.95, 0.05, 'DEBUG',
                fontsize=50, color='gray',
                ha='center', va='bottom', alpha=0.5, rotation=20)
        if scaling_enabled:
            pyplot.text(0.05, 0.95, 'SCALED',
                fontsize=50, color='gray',
                ha='center', va='top', alpha=0.5, rotation=20)

    pyplot.suptitle(args.results_file.lstrip('./')[:-5].replace("_", " "), va="center")

    pyplot.tight_layout()
    if args.output:
        pyplot.savefig(args.output)
    else:
        pyplot.show()

if __name__ == "__main__":
    main()