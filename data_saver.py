import os
import serial
import numpy as np
import matplotlib.pyplot as plt

data_folder = "./data/pops/"
# data_folder = "./data/noise/"
buffer_size = 16000

print("Starting data recording, hit Ctrl+C to stop it.")

received_messages = []
with serial.Serial(port="COM9", baudrate=500000) as serial:
    while True:
        try:
            if serial.in_waiting > 0:
                message = serial.read_all()
                received_messages.append(message)
        except KeyboardInterrupt:
            break

frames = b"".join(received_messages).split(b"end_of_frame")
frames = frames[1:-1]  # leave away first and last frame

# check if all frames are of the same length
frame_lengths = list(set([len(frame) for frame in frames]))
assert (
    len(frame_lengths) == 1
), "Error: The received data is corrupted, the data frames are not of the same length."
assert (
    frame_lengths[0] == 3 * buffer_size
), "Error: The received data is corrupted, the data frames are not of the expected length."

sound_pieces = []
pop_pieces = []
for frame in frames:

    sound_piece = np.frombuffer(frame, dtype=np.int16, count=buffer_size)
    pop_piece = np.frombuffer(
        frame[2 * buffer_size :], dtype=np.uint8, count=buffer_size
    )

    sound_pieces.append(sound_piece)
    pop_pieces.append(pop_piece)

sound = np.concatenate(sound_pieces)
pop = np.concatenate(pop_pieces)

num_files = len(os.listdir(data_folder)) // 2
np.save(data_folder + f"sound_{num_files}.npy", sound)
np.save(data_folder + f"pop_{num_files}.npy", pop)

print(f"Sample {num_files} has been saved to {data_folder}.")

plt.plot(sound)
plt.plot(pop * np.mean(np.abs(sound)))
plt.show()