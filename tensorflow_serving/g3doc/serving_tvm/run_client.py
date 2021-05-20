import numpy as np
import json
import requests

data = np.random.uniform(size=(1, 224, 224, 3)).astype('float32')

data = json.dumps({"signature_name": "serving_default", "instances": data.tolist()})
print('Data: {} ... {}'.format(data[:50], data[len(data)-52:]))

headers = {"content-type": "application/json"}
json_response = requests.post('http://localhost:6004/v1/models/tvm_test:predict', data=data, headers=headers)
print("Json Resp:", json_response)
predictions = json.loads(json_response.text)['predictions']
print("Predictions:", len(predictions[0]))
