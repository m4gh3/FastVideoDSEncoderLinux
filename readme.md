FastVideoDS EncoderLinux
===================
This is a fork of the [Gericom](https://github.com/Gericom)'s Encoder for the FastVideoDS format.
The aim of this fork is to make as easy as possible to use FastVideoDSEncoder on Linux
As of now only a build as a binary containing all the dependencies is available ( so no need to install ffmpeg or .NET )

Use [FastVideoDS Player](https://github.com/Gericom/FastVideoDSPlayer) to play back the encoded videos.

## Usage
    FastVideoDSEncoder [-j jobs] input output.fv

* **-j *jobs*** Number of concurrent jobs (optional, default: cpu threads / 1.5)
* ***input*** The input video file. Most formats are supported through FFmpeg.
* ***output.fv*** The output video file.

## Libraries Used
* [CommandLineParser](https://github.com/commandlineparser/commandline)
* [FFmpeg.AutoGen](https://github.com/Ruslan-B/FFmpeg.AutoGen)
* [FFmpeg](https://ffmpeg.org/)
