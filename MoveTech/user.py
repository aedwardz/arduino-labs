import requests

# Server URL (same as the one in your C++ code)
print("Menu:\n\tSet timer [1]\n\tView time set [2]\n")
val = int(input())

if val == 1:
    time = input("How much time would you like to set?:\n")
    endpoint = f"/time/{time}"
elif val == 2:
    endpoint = f"/time"

BASE_URL = f"http://ec2-35-91-172-76.us-west-2.compute.amazonaws.com:5000/{endpoint}"

# Function to send GET request to the server
def send_request_to_server():
    try:
        # Send GET request
        response = requests.get(BASE_URL)

        # Check if the request was successful
        if response.status_code == 200:
            print("Request sent successfully!")
            print("Server Response:", response.text)
        else:
            print(f"Failed to send request. HTTP Status Code: {response.status_code}")
    
    except requests.exceptions.RequestException as e:
        print(f"An error occurred: {e}")

# Main
if __name__ == "__main__":
    send_request_to_server()