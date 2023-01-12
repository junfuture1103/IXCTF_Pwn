FROM ubuntu:22.04

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y xinetd

ENV TERM=linux

RUN useradd -m simple_fsb
WORKDIR /home/simple_fsb/prob

ADD ./prob/simple_fsb /home/simple_fsb/prob
ADD ./prob/flag /
ADD simple_fsb /etc/xinetd.d

RUN chown simple_fsb:root /home/simple_fsb/prob/*
RUN chown simple_fsb:root /home/simple_fsb/prob

RUN chmod +x /home/simple_fsb/prob/simple_fsb
RUN cd /home/simple_fsb/prob
RUN echo "simple_fsb 10050/tcp" >> /etc/services

CMD ["/usr/sbin/xinetd","-dontfork"]
