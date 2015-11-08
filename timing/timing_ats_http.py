###############################################################################
# timing_ats_http.py
# 
# Timing HTTP requests with Apache Bench
###############################################################################

import subprocess
import argparse
import time
import re

AB_FORMAT = 'ab -q %s -c %d -n %d %s %s'
GNUPLOT_FORMAT = 'gnuplot -e "out_file=\'%s.jpeg\'" \
-e "data_file=\'%s.tsv\'" -e "plot_title=\'%s\'" plot_timing_ats_http.gp'

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('urls_file', help='file containing URLs to test')
    parser.add_argument('res_dir', help='directory to write results to')
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
        if not args.gnuplot:
            out = '<html><body><h2>Timing HTTP Requests @ '+timestamp+'</h2><hr>'
        for url in f:
            url = url.strip()
            output = '-w'
            out_file_name = args.res_dir+timestamp+'-'+ \
                url.replace('/', '').replace(':', '')
            if args.gnuplot:
                output = '-g '+out_file_name+'.tsv'
            ab_command = AB_FORMAT % (args.proxy, args.concurrent_requests,
                                      args.num_requests, output, url)
            proc = subprocess.Popen(ab_command, stdout=subprocess.PIPE,
                shell=True)
            if args.gnuplot:
                out += proc.communicate()[0]+ \
                    '\n======================================================================\n\n'
                gnuplot_command = GNUPLOT_FORMAT % (out_file_name, out_file_name,
                    url+' n='+str(args.num_requests)+' c='+str(args.concurrent_requests))
                subprocess.call(gnuplot_command, shell=True)
            else:
                out += '<table>'+proc.communicate()[0].split('<table >')[1]+'<hr>'
        if args.gnuplot:
            out_file_name += '.txt'
        else:
            out += '</body></html>'
            out_file_name += '.html'

        with open(out_file_name, 'w') as f:
            f.write(out)


if __name__ == '__main__':
    main()
