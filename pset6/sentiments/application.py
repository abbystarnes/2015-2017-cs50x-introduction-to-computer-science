from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, count=100)
    if not tweets:
        return redirect(url_for("index"))

    # TODO
    analyzer = Analyzer('positive-words.txt', 'negative-words.txt')
    
     # analyze word
    positive = 0
    negative = 0
    neutral = 0
    total = 0
    
    for tweet in tweets:
        
        score = analyzer.analyze(tweet)
        if score > 0.0:
            positive += 1
            total += 1
        elif score < 0.0:
            negative += 1
            total += 1
        else:
            neutral += 1
            total += 1
    positive = positive/total
    negative = negative/total
    neutral = neutral/total
    print(positive, 'pos', negative, 'neg', neutral, 'neut')


    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
