#!/usr/bin/env bash

rsync -avhPr . sni038@login.uib.no:~/236-mandatory3
ssh sni038@login.uib.no "rsync -avhPr 236-mandatory3 sni038@brake.ii.uib.no:~/236-mandatory3"