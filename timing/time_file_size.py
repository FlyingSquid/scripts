###############################################################################
# timing_ats_http.py
# 
# Timing HTTP requests with Apache Bench
###############################################################################

import subprocess
import argparse
import time
import re

AB_FORMAT = 'ab -q %s -c %d -n %d %s'
GNUPLOT_FORMAT = 'gnuplot -e "out_file=\'%s.jpeg\'" \
-e "data_file=\'%s.tsv\'" -e "plot_title=\'%s\'" plot_time_file_size.gp'

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('urls_file', help='file containing URLs to test')
    parser.add_argument('-g', '--gnuplot', action='store_true',
        help='output to gnuplot format instead of HTML')
    parser.add_argument('-x', '--proxy', default='',
        help='HTTP proxy and port to route requests through in format PROXYIP:PORT')
    parser.add_argument('-n', '--num_requests', type=int, default=2,
        help='number of requests to perform for each URL')
    parser.add_argument('-c', '--concurrent_requests', type=int, default=1,
        help='max number of requests to perform concurrently for each URL')
    args = parser.parse_args()
    if args.proxy:
        args.proxy = '-X '+args.proxy
    return args


def main():
    args = parse_args()

    with open(args.urls_file, 'r') as f:
        timestamp = str(time.time())
        out = ''
        data = ''
        for url in f:
            url = url.strip()
            ab_command = AB_FORMAT % (args.proxy, args.concurrent_requests,
                                      args.num_requests, url)
            proc = subprocess.Popen(ab_command, stdout=subprocess.PIPE,
                shell=True)
            if args.gnuplot:
                result = proc.communicate()[0]+ \
                    '\n======================================================================\n\n'
                out += result
                size = re.search(r'Document Length:\s*(\w+)', result).group(1).strip()
                print size
                ms = re.search(r'Time per request:\s*(\w+)', result).group(1).strip()
                print ms
                data += size + '\t' + ms + '\n'
                print data
        if args.gnuplot:
            out_file_name = timestamp+'-benchmarking.txt'

        with open(out_file_name, 'w') as f:
            f.write(out)
        tsv_file = 'all.tsv'
        with open(tsv_file, 'w') as g:
            g.write(data)

        gnuplot_command = 'gnuplot -e "out_file=\'all.jpeg\'" \
        -e "data_file=\'all.tsv\'" -e "plot_title=\'Time vs. file size\'" plot_time_file_size.gp'

        subprocess.call(gnuplot_command, shell=True)


if __name__ == '__main__':
    main()
