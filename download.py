import requests
import os
from tqdm import tqdm

model_name = "microsoft/BitNet-b1.58-2B-4T-gguf"
local_dir = "models/BitNet-b1.58-2B-4T"
filename = "ggml-model-i2_s.gguf"

os.makedirs(local_dir, exist_ok=True)
filepath = os.path.join(local_dir, filename)

url = f"https://huggingface.co/{model_name}/resolve/main/{filename}"

try:
    print(f"Downloading {url} to {filepath}")
    response = requests.get(url, stream=True, verify=False)  # Added verify=False
    response.raise_for_status()

    total_size_in_bytes = int(response.headers.get('content-length', 0))
    block_size = 1024
    progress_bar = tqdm(total=total_size_in_bytes, unit='iB', unit_scale=True)

    with open(filepath, 'wb') as file:
        for data in response.iter_content(block_size):
            progress_bar.update(len(data))
            file.write(data)
    progress_bar.close()

    if total_size_in_bytes != 0 and progress_bar.n != total_size_in_bytes:
        print("ERROR, something went wrong")
    else:
        print(f"Successfully downloaded {filename} to {local_dir}")

except requests.exceptions.RequestException as e:
    print(f"Error downloading {url}: {e}")
except Exception as e:
    print(f"An unexpected error occurred: {e}")