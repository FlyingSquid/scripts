# Benchmarking Scripts

### timing_ats_http.py

`Python`, `ApacheBench`, and `gnuplot` must be installed.

Wrapper for [ApacheBench](http://httpd.apache.org/docs/current/programs/ab.html) for timing HTTP requests.

        usage: timing_ats_http.py [-h] [-g] [-x PROXY] [-n NUM_REQUESTS]
                          [-c CONCURRENT_REQUESTS]
                          urls_file res_dir

        positional arguments:
          urls_file             file containing URLs to test
          res_dir               directory to write results to

        optional arguments:
          -h, --help            show this help message and exit
          -g, --gnuplot         output to gnuplot format instead of HTML
          -x PROXY, --proxy PROXY
                                HTTP proxy and port to route requests through in
                                format PROXYIP:PORT
          -n NUM_REQUESTS, --num_requests NUM_REQUESTS
                                number of requests to perform for each URL
          -c CONCURRENT_REQUESTS, --concurrent_requests CONCURRENT_REQUESTS
                                max number of requests to perform concurrently for
                                each URL

Output by default is HTML table of statistics for each URL in provided file with min, max, mean of request times in ms (also broken down ). As shown above, `-g` option outputs graph generated with `gnuplot` of request/response times, `.tsv` data for request/response times, and plaintext formatted overall statistics for each URL.
