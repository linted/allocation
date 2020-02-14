#!/usr/bin/env python3
import numpy as np
from matplotlib import pyplot
import json
import argparse


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("results_file", help="google benchmark results json output")
    args = parser.parse_args()

    # print(dir(args))
    with open(args.results_file, 'r') as fin:
        results = json.load(fin)

    prog_name = results['context']['executable']
    debug = results['context']['library_build_type'] != 'release'

    benchmarks = {}

    for test in results['benchmarks']:
        if test['run_type'] == "aggregate":
            if not benchmarks.get(test['run_name'], False):
                benchmarks[test['run_name']] = {
                    'mean':None, 
                    'median':None, 
                    'stddev':None
                }
            benchmarks[test['run_name']][test['aggregate_name']] = test["cpu_time"]
    
    y_ticks = np.arange(len(benchmarks))

    pyplot.barh(y_ticks,
        [x['mean'] for x in benchmarks.values()], 
        xerr=[x['stddev'] for x in benchmarks.values()])

    pyplot.yticks(y_ticks, labels=[x for x in benchmarks.keys()])

    pyplot.xlabel("time in {}".format(results['benchmarks'][0]['time_unit']))

    pyplot.title = prog_name
    if debug:
        pyplot.text(0.95, 0.05, 'DEBUG',
            fontsize=50, color='gray',
            ha='right', va='center', alpha=0.5)

    pyplot.tight_layout()
    pyplot.show()

if __name__ == "__main__":
    main()