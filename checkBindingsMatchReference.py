#!/usr/bin/python

import os
from subprocess import call


def executeExamples(folder):
	results = dict();

	for filename in os.listdir(folder):
		example, extension = filename.split(".")

		if os.access(os.path.join(folder, filename), os.X_OK):
			results[example] = os.popen(os.path.join(folder, filename)).read()

	return results

referenceResults = executeExamples('examples/');

results = dict()
results['python'] = executeExamples("bindings-python/examples/")

for binding, results in results.items():
	for example, referenceResult in referenceResults.items():
		if example not in results.keys():
			print "Example not found in binding:", binding, " when looking for example:", example
			continue;

		if results[example] != referenceResult:
			print "Result", example, "for binding:", binding, " is not equal to the reference result. \n\nBinding's version:\n", results[example], "\n\nReference version:\n", referenceResult
			continue;
	
	
